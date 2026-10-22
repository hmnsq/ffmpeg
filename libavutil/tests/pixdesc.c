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

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/macros.h"
#अन्तर्भाव "libavutil/pixdesc.h"
#अन्तर्भाव "libavutil/pixfmt.h"

/*
 * from_name() may legitimately map to a different index when two enum
 * values share the same name string (e.g. AVCOL_PRI_RESERVED0 and
 * AVCOL_PRI_RESERVED both use "reserved"). Accept that as long as
 * name(back) equals name(i).
 */
स्थिर पूर्णांक check_name_equivalence(स्थिरांक अक्षर *name, स्थिरांक अक्षर *back_name)
{
    परत back_name && !म_भेद(name, back_name);
}

स्थिर पूर्णांक test_pix_fmt_round_trip(शून्य)
{
    पूर्णांक fail = 0;
    साठी (पूर्णांक i = 0; i < AV_PIX_FMT_NB; i++) {
        स्थिरांक अक्षर *name = av_get_pix_fmt_name(i);
        जर (!name)
            सुरूठेवा;
        जर (av_get_pix_fmt(name) != i)
            fail++;
    }
    परत fail;
}

स्थिर पूर्णांक test_color_range_round_trip(शून्य)
{
    पूर्णांक fail = 0;
    साठी (पूर्णांक i = 0; i < AVCOL_RANGE_NB; i++) {
        स्थिरांक अक्षर *name = av_color_range_name(i);
        जर (!name)
            सुरूठेवा;
        पूर्णांक back = av_color_range_from_name(name);
        जर (back < 0 || !check_name_equivalence(name, av_color_range_name(back)))
            fail++;
    }
    परत fail;
}

स्थिर पूर्णांक test_color_primaries_round_trip(शून्य)
{
    पूर्णांक fail = 0;
    साठी (पूर्णांक i = 0; i < AVCOL_PRI_NB; i++) {
        स्थिरांक अक्षर *name = av_color_primaries_name(i);
        जर (!name)
            सुरूठेवा;
        पूर्णांक back = av_color_primaries_from_name(name);
        जर (back < 0 || !check_name_equivalence(name, av_color_primaries_name(back)))
            fail++;
    }
    परत fail;
}

स्थिर पूर्णांक test_color_transfer_round_trip(शून्य)
{
    पूर्णांक fail = 0;
    साठी (पूर्णांक i = 0; i < AVCOL_TRC_NB; i++) {
        स्थिरांक अक्षर *name = av_color_transfer_name(i);
        जर (!name)
            सुरूठेवा;
        पूर्णांक back = av_color_transfer_from_name(name);
        जर (back < 0 || !check_name_equivalence(name, av_color_transfer_name(back)))
            fail++;
    }
    परत fail;
}

स्थिर पूर्णांक test_color_space_round_trip(शून्य)
{
    पूर्णांक fail = 0;
    साठी (पूर्णांक i = 0; i < AVCOL_SPC_NB; i++) {
        स्थिरांक अक्षर *name = av_color_space_name(i);
        जर (!name)
            सुरूठेवा;
        पूर्णांक back = av_color_space_from_name(name);
        जर (back < 0 || !check_name_equivalence(name, av_color_space_name(back)))
            fail++;
    }
    परत fail;
}

स्थिर पूर्णांक test_chroma_location_round_trip(शून्य)
{
    पूर्णांक fail = 0;
    साठी (पूर्णांक i = 0; i < AVCHROMA_LOC_NB; i++) {
        स्थिरांक अक्षर *name = av_chroma_location_name(i);
        जर (!name)
            सुरूठेवा;
        पूर्णांक back = av_chroma_location_from_name(name);
        जर (back < 0 || !check_name_equivalence(name, av_chroma_location_name(back)))
            fail++;
    }
    परत fail;
}

स्थिर पूर्णांक test_alpha_mode_round_trip(शून्य)
{
    पूर्णांक fail = 0;
    साठी (पूर्णांक i = 0; i < AVALPHA_MODE_NB; i++) {
        स्थिरांक अक्षर *name = av_alpha_mode_name(i);
        जर (!name)
            सुरूठेवा;
        पूर्णांक back = av_alpha_mode_from_name(name);
        जर (back < 0 || !check_name_equivalence(name, av_alpha_mode_name(back)))
            fail++;
    }
    परत fail;
}

स्थिर पूर्णांक test_chroma_location_pos_round_trip(शून्य)
{
    पूर्णांक fail = 0;
    साठी (पूर्णांक i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        पूर्णांक xpos, ypos;
        जर (av_chroma_location_enum_to_pos(&xpos, &ypos, i) < 0) {
            fail++;
            सुरूठेवा;
        }
        जर ((पूर्णांक)av_chroma_location_pos_to_enum(xpos, ypos) != i)
            fail++;
    }
    परत fail;
}

पूर्णांक main(शून्य)
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
    साठी (पूर्णांक i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        जर (!desc || !desc->name) {
            skip++;
            सुरूठेवा;
        }
        जर (skip) {
            म_लिखो("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        म_लिखो("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_bits_per_pixel(desc),
               av_pix_fmt_मोजणी_planes(i));
    }

    परत 0;
}
