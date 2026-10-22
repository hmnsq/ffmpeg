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

#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/macros.h"
#समावेश "libavutil/pixdesc.h"
#समावेश "libavutil/pixfmt.h"

/*
 * from_name() may legitimately map to a different index when two enum
 * values share the same name string (e.g. AVCOL_PRI_RESERVED0 and
 * AVCOL_PRI_RESERVED both use "reserved"). Accept that as long as
 * name(back) equals name(i).
 */
अटल पूर्णांक check_name_equivalence(स्थिर अक्षर *name, स्थिर अक्षर *back_name)
{
    वापस back_name && !म_भेद(name, back_name);
}

अटल पूर्णांक test_pix_fmt_round_trip(व्योम)
{
    पूर्णांक fail = 0;
    क्रम (पूर्णांक i = 0; i < AV_PIX_FMT_NB; i++) {
        स्थिर अक्षर *name = av_get_pix_fmt_name(i);
        अगर (!name)
            जारी;
        अगर (av_get_pix_fmt(name) != i)
            fail++;
    }
    वापस fail;
}

अटल पूर्णांक test_color_range_round_trip(व्योम)
{
    पूर्णांक fail = 0;
    क्रम (पूर्णांक i = 0; i < AVCOL_RANGE_NB; i++) {
        स्थिर अक्षर *name = av_color_range_name(i);
        अगर (!name)
            जारी;
        पूर्णांक back = av_color_range_from_name(name);
        अगर (back < 0 || !check_name_equivalence(name, av_color_range_name(back)))
            fail++;
    }
    वापस fail;
}

अटल पूर्णांक test_color_primaries_round_trip(व्योम)
{
    पूर्णांक fail = 0;
    क्रम (पूर्णांक i = 0; i < AVCOL_PRI_NB; i++) {
        स्थिर अक्षर *name = av_color_primaries_name(i);
        अगर (!name)
            जारी;
        पूर्णांक back = av_color_primaries_from_name(name);
        अगर (back < 0 || !check_name_equivalence(name, av_color_primaries_name(back)))
            fail++;
    }
    वापस fail;
}

अटल पूर्णांक test_color_transfer_round_trip(व्योम)
{
    पूर्णांक fail = 0;
    क्रम (पूर्णांक i = 0; i < AVCOL_TRC_NB; i++) {
        स्थिर अक्षर *name = av_color_transfer_name(i);
        अगर (!name)
            जारी;
        पूर्णांक back = av_color_transfer_from_name(name);
        अगर (back < 0 || !check_name_equivalence(name, av_color_transfer_name(back)))
            fail++;
    }
    वापस fail;
}

अटल पूर्णांक test_color_space_round_trip(व्योम)
{
    पूर्णांक fail = 0;
    क्रम (पूर्णांक i = 0; i < AVCOL_SPC_NB; i++) {
        स्थिर अक्षर *name = av_color_space_name(i);
        अगर (!name)
            जारी;
        पूर्णांक back = av_color_space_from_name(name);
        अगर (back < 0 || !check_name_equivalence(name, av_color_space_name(back)))
            fail++;
    }
    वापस fail;
}

अटल पूर्णांक test_chroma_location_round_trip(व्योम)
{
    पूर्णांक fail = 0;
    क्रम (पूर्णांक i = 0; i < AVCHROMA_LOC_NB; i++) {
        स्थिर अक्षर *name = av_chroma_location_name(i);
        अगर (!name)
            जारी;
        पूर्णांक back = av_chroma_location_from_name(name);
        अगर (back < 0 || !check_name_equivalence(name, av_chroma_location_name(back)))
            fail++;
    }
    वापस fail;
}

अटल पूर्णांक test_alpha_mode_round_trip(व्योम)
{
    पूर्णांक fail = 0;
    क्रम (पूर्णांक i = 0; i < AVALPHA_MODE_NB; i++) {
        स्थिर अक्षर *name = av_alpha_mode_name(i);
        अगर (!name)
            जारी;
        पूर्णांक back = av_alpha_mode_from_name(name);
        अगर (back < 0 || !check_name_equivalence(name, av_alpha_mode_name(back)))
            fail++;
    }
    वापस fail;
}

अटल पूर्णांक test_chroma_location_pos_round_trip(व्योम)
{
    पूर्णांक fail = 0;
    क्रम (पूर्णांक i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        पूर्णांक xpos, ypos;
        अगर (av_chroma_location_enum_to_pos(&xpos, &ypos, i) < 0) {
            fail++;
            जारी;
        }
        अगर ((पूर्णांक)av_chroma_location_pos_to_enum(xpos, ypos) != i)
            fail++;
    }
    वापस fail;
}

पूर्णांक मुख्य(व्योम)
{
    पूर्णांक skip = 0;

    म_लिखो("Testing av_get_pix_fmt() / av_get_pix_fmt_name() round-trip\n");
    म_लिखो("  result: %s\n",
           test_pix_fmt_round_trip() ? "FAIL" : "OK");

    म_लिखो("\nTesting av_color_*_name() / av_color_*_from_name() round-trips\n");
    म_लिखो("  av_color_range:     %s\n",
           test_color_range_round_trip()     ? "FAIL" : "OK");
    म_लिखो("  av_color_primaries: %s\n",
           test_color_primaries_round_trip() ? "FAIL" : "OK");
    म_लिखो("  av_color_transfer:  %s\n",
           test_color_transfer_round_trip()  ? "FAIL" : "OK");
    म_लिखो("  av_color_space:     %s\n",
           test_color_space_round_trip()     ? "FAIL" : "OK");
    म_लिखो("  av_chroma_location: %s\n",
           test_chroma_location_round_trip() ? "FAIL" : "OK");
    म_लिखो("  av_alpha_mode:      %s\n",
           test_alpha_mode_round_trip()      ? "FAIL" : "OK");

    म_लिखो("\nTesting av_chroma_location_enum_to_pos / pos_to_enum round-trip\n");
    म_लिखो("  result: %s\n",
           test_chroma_location_pos_round_trip() ? "FAIL" : "OK");

    म_लिखो("\nTesting pixel format descriptors\n");
    क्रम (पूर्णांक i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        अगर (!desc || !desc->name) {
            skip++;
            जारी;
        }
        अगर (skip) {
            म_लिखो("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        म_लिखो("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_bits_per_pixel(desc),
               av_pix_fmt_गिनती_planes(i));
    }

    वापस 0;
}
