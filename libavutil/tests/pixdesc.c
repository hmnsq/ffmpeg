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

#شامل <stdio.h>
#شامل <string.h>

#شامل "libavutil/macros.h"
#شامل "libavutil/pixdesc.h"
#شامل "libavutil/pixfmt.h"

/*
 * from_name() may legitimately map to a different index when two enum
 * values share the same name string (e.g. AVCOL_PRI_RESERVED0 and
 * AVCOL_PRI_RESERVED both use "reserved"). Accept that as long as
 * name(back) equals name(i).
 */
ساکن صحیح check_name_equivalence(ثابت حرف *name, ثابت حرف *عقب_name)
{
    واپس عقب_name && !strcmp(name, عقب_name);
}

ساکن صحیح test_pix_fmt_باری_trip(خالی)
{
    صحیح fail = 0;
    برائے (صحیح i = 0; i < AV_PIX_FMT_NB; i++) {
        ثابت حرف *name = av_get_pix_fmt_name(i);
        اگر (!name)
            جاری;
        اگر (av_get_pix_fmt(name) != i)
            fail++;
    }
    واپس fail;
}

ساکن صحیح test_color_range_باری_trip(خالی)
{
    صحیح fail = 0;
    برائے (صحیح i = 0; i < AVCOL_RANGE_NB; i++) {
        ثابت حرف *name = av_color_range_name(i);
        اگر (!name)
            جاری;
        صحیح عقب = av_color_range_from_name(name);
        اگر (عقب < 0 || !check_name_equivalence(name, av_color_range_name(عقب)))
            fail++;
    }
    واپس fail;
}

ساکن صحیح test_color_primaries_باری_trip(خالی)
{
    صحیح fail = 0;
    برائے (صحیح i = 0; i < AVCOL_PRI_NB; i++) {
        ثابت حرف *name = av_color_primaries_name(i);
        اگر (!name)
            جاری;
        صحیح عقب = av_color_primaries_from_name(name);
        اگر (عقب < 0 || !check_name_equivalence(name, av_color_primaries_name(عقب)))
            fail++;
    }
    واپس fail;
}

ساکن صحیح test_color_transfer_باری_trip(خالی)
{
    صحیح fail = 0;
    برائے (صحیح i = 0; i < AVCOL_TRC_NB; i++) {
        ثابت حرف *name = av_color_transfer_name(i);
        اگر (!name)
            جاری;
        صحیح عقب = av_color_transfer_from_name(name);
        اگر (عقب < 0 || !check_name_equivalence(name, av_color_transfer_name(عقب)))
            fail++;
    }
    واپس fail;
}

ساکن صحیح test_color_space_باری_trip(خالی)
{
    صحیح fail = 0;
    برائے (صحیح i = 0; i < AVCOL_SPC_NB; i++) {
        ثابت حرف *name = av_color_space_name(i);
        اگر (!name)
            جاری;
        صحیح عقب = av_color_space_from_name(name);
        اگر (عقب < 0 || !check_name_equivalence(name, av_color_space_name(عقب)))
            fail++;
    }
    واپس fail;
}

ساکن صحیح test_chroma_location_باری_trip(خالی)
{
    صحیح fail = 0;
    برائے (صحیح i = 0; i < AVCHROMA_LOC_NB; i++) {
        ثابت حرف *name = av_chroma_location_name(i);
        اگر (!name)
            جاری;
        صحیح عقب = av_chroma_location_from_name(name);
        اگر (عقب < 0 || !check_name_equivalence(name, av_chroma_location_name(عقب)))
            fail++;
    }
    واپس fail;
}

ساکن صحیح test_alpha_منوال_باری_trip(خالی)
{
    صحیح fail = 0;
    برائے (صحیح i = 0; i < AVALPHA_منوال_NB; i++) {
        ثابت حرف *name = av_alpha_منوال_name(i);
        اگر (!name)
            جاری;
        صحیح عقب = av_alpha_منوال_from_name(name);
        اگر (عقب < 0 || !check_name_equivalence(name, av_alpha_منوال_name(عقب)))
            fail++;
    }
    واپس fail;
}

ساکن صحیح test_chroma_location_pos_باری_trip(خالی)
{
    صحیح fail = 0;
    برائے (صحیح i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        صحیح xpos, ypos;
        اگر (av_chroma_location_enum_مقصد_pos(&xpos, &ypos, i) < 0) {
            fail++;
            جاری;
        }
        اگر ((صحیح)av_chroma_location_pos_مقصد_enum(xpos, ypos) != i)
            fail++;
    }
    واپس fail;
}

صحیح مین(خالی)
{
    صحیح skip = 0;

    لکھو("Testing av_get_pix_fmt() / av_get_pix_fmt_name() round-trip\n");
    لکھو("  result: %s\n",
           test_pix_fmt_باری_trip() ? "FAIL" : "OK");

    لکھو("\nTesting av_color_*_name() / av_color_*_from_name() round-trips\n");
    لکھو("  av_color_range:     %s\n",
           test_color_range_باری_trip()     ? "FAIL" : "OK");
    لکھو("  av_color_primaries: %s\n",
           test_color_primaries_باری_trip() ? "FAIL" : "OK");
    لکھو("  av_color_transfer:  %s\n",
           test_color_transfer_باری_trip()  ? "FAIL" : "OK");
    لکھو("  av_color_space:     %s\n",
           test_color_space_باری_trip()     ? "FAIL" : "OK");
    لکھو("  av_chroma_location: %s\n",
           test_chroma_location_باری_trip() ? "FAIL" : "OK");
    لکھو("  av_alpha_mode:      %s\n",
           test_alpha_منوال_باری_trip()      ? "FAIL" : "OK");

    لکھو("\nTesting av_chroma_location_enum_to_pos / pos_to_enum round-trip\n");
    لکھو("  result: %s\n",
           test_chroma_location_pos_باری_trip() ? "FAIL" : "OK");

    لکھو("\nTesting pixel format descriptors\n");
    برائے (صحیح i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        اگر (!desc || !desc->name) {
            skip++;
            جاری;
        }
        اگر (skip) {
            لکھو("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        لکھو("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_بٹ_فی_pixel(desc),
               av_pix_fmt_گنتی_planes(i));
    }

    واپس 0;
}
