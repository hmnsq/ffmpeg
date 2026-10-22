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
स्थिर पूर्णाङ्क check_name_equivalence(ध्रुव वर्ण *name, ध्रुव वर्ण *पृष्ठभागः_name)
{
    प्रत्यागम पृष्ठभागः_name && !वाक्यं_तुलय(name, पृष्ठभागः_name);
}

स्थिर पूर्णाङ्क test_pix_fmt_आवर्तनम्_trip(शून्य)
{
    पूर्णाङ्क fail = 0;
    प्रति (पूर्णाङ्क i = 0; i < AV_PIX_FMT_NB; i++) {
        ध्रुव वर्ण *name = av_get_pix_fmt_name(i);
        यदि (!name)
            अनुवर्त;
        यदि (av_get_pix_fmt(name) != i)
            fail++;
    }
    प्रत्यागम fail;
}

स्थिर पूर्णाङ्क test_color_range_आवर्तनम्_trip(शून्य)
{
    पूर्णाङ्क fail = 0;
    प्रति (पूर्णाङ्क i = 0; i < AVCOL_RANGE_NB; i++) {
        ध्रुव वर्ण *name = av_color_range_name(i);
        यदि (!name)
            अनुवर्त;
        पूर्णाङ्क पृष्ठभागः = av_color_range_from_name(name);
        यदि (पृष्ठभागः < 0 || !check_name_equivalence(name, av_color_range_name(पृष्ठभागः)))
            fail++;
    }
    प्रत्यागम fail;
}

स्थिर पूर्णाङ्क test_color_primaries_आवर्तनम्_trip(शून्य)
{
    पूर्णाङ्क fail = 0;
    प्रति (पूर्णाङ्क i = 0; i < AVCOL_PRI_NB; i++) {
        ध्रुव वर्ण *name = av_color_primaries_name(i);
        यदि (!name)
            अनुवर्त;
        पूर्णाङ्क पृष्ठभागः = av_color_primaries_from_name(name);
        यदि (पृष्ठभागः < 0 || !check_name_equivalence(name, av_color_primaries_name(पृष्ठभागः)))
            fail++;
    }
    प्रत्यागम fail;
}

स्थिर पूर्णाङ्क test_color_transfer_आवर्तनम्_trip(शून्य)
{
    पूर्णाङ्क fail = 0;
    प्रति (पूर्णाङ्क i = 0; i < AVCOL_TRC_NB; i++) {
        ध्रुव वर्ण *name = av_color_transfer_name(i);
        यदि (!name)
            अनुवर्त;
        पूर्णाङ्क पृष्ठभागः = av_color_transfer_from_name(name);
        यदि (पृष्ठभागः < 0 || !check_name_equivalence(name, av_color_transfer_name(पृष्ठभागः)))
            fail++;
    }
    प्रत्यागम fail;
}

स्थिर पूर्णाङ्क test_color_space_आवर्तनम्_trip(शून्य)
{
    पूर्णाङ्क fail = 0;
    प्रति (पूर्णाङ्क i = 0; i < AVCOL_SPC_NB; i++) {
        ध्रुव वर्ण *name = av_color_space_name(i);
        यदि (!name)
            अनुवर्त;
        पूर्णाङ्क पृष्ठभागः = av_color_space_from_name(name);
        यदि (पृष्ठभागः < 0 || !check_name_equivalence(name, av_color_space_name(पृष्ठभागः)))
            fail++;
    }
    प्रत्यागम fail;
}

स्थिर पूर्णाङ्क test_chroma_location_आवर्तनम्_trip(शून्य)
{
    पूर्णाङ्क fail = 0;
    प्रति (पूर्णाङ्क i = 0; i < AVCHROMA_LOC_NB; i++) {
        ध्रुव वर्ण *name = av_chroma_location_name(i);
        यदि (!name)
            अनुवर्त;
        पूर्णाङ्क पृष्ठभागः = av_chroma_location_from_name(name);
        यदि (पृष्ठभागः < 0 || !check_name_equivalence(name, av_chroma_location_name(पृष्ठभागः)))
            fail++;
    }
    प्रत्यागम fail;
}

स्थिर पूर्णाङ्क test_alpha_बहुलकम्_आवर्तनम्_trip(शून्य)
{
    पूर्णाङ्क fail = 0;
    प्रति (पूर्णाङ्क i = 0; i < AVALPHA_बहुलकम्_NB; i++) {
        ध्रुव वर्ण *name = av_alpha_बहुलकम्_name(i);
        यदि (!name)
            अनुवर्त;
        पूर्णाङ्क पृष्ठभागः = av_alpha_बहुलकम्_from_name(name);
        यदि (पृष्ठभागः < 0 || !check_name_equivalence(name, av_alpha_बहुलकम्_name(पृष्ठभागः)))
            fail++;
    }
    प्रत्यागम fail;
}

स्थिर पूर्णाङ्क test_chroma_location_pos_आवर्तनम्_trip(शून्य)
{
    पूर्णाङ्क fail = 0;
    प्रति (पूर्णाङ्क i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        पूर्णाङ्क xpos, ypos;
        यदि (av_chroma_location_enum_गन्तव्यम्_pos(&xpos, &ypos, i) < 0) {
            fail++;
            अनुवर्त;
        }
        यदि ((पूर्णाङ्क)av_chroma_location_pos_गन्तव्यम्_enum(xpos, ypos) != i)
            fail++;
    }
    प्रत्यागम fail;
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    पूर्णाङ्क skip = 0;

    प्रारूप_लिख("Testing av_get_pix_fmt() / av_get_pix_fmt_name() round-trip\n");
    प्रारूप_लिख("  result: %s\n",
           test_pix_fmt_आवर्तनम्_trip() ? "FAIL" : "OK");

    प्रारूप_लिख("\nTesting av_color_*_name() / av_color_*_from_name() round-trips\n");
    प्रारूप_लिख("  av_color_range:     %s\n",
           test_color_range_आवर्तनम्_trip()     ? "FAIL" : "OK");
    प्रारूप_लिख("  av_color_primaries: %s\n",
           test_color_primaries_आवर्तनम्_trip() ? "FAIL" : "OK");
    प्रारूप_लिख("  av_color_transfer:  %s\n",
           test_color_transfer_आवर्तनम्_trip()  ? "FAIL" : "OK");
    प्रारूप_लिख("  av_color_space:     %s\n",
           test_color_space_आवर्तनम्_trip()     ? "FAIL" : "OK");
    प्रारूप_लिख("  av_chroma_location: %s\n",
           test_chroma_location_आवर्तनम्_trip() ? "FAIL" : "OK");
    प्रारूप_लिख("  av_alpha_mode:      %s\n",
           test_alpha_बहुलकम्_आवर्तनम्_trip()      ? "FAIL" : "OK");

    प्रारूप_लिख("\nTesting av_chroma_location_enum_to_pos / pos_to_enum round-trip\n");
    प्रारूप_लिख("  result: %s\n",
           test_chroma_location_pos_आवर्तनम्_trip() ? "FAIL" : "OK");

    प्रारूप_लिख("\nTesting pixel format descriptors\n");
    प्रति (पूर्णाङ्क i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        यदि (!desc || !desc->name) {
            skip++;
            अनुवर्त;
        }
        यदि (skip) {
            प्रारूप_लिख("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        प्रारूप_लिख("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_द्वयङ्काः_प्रत्येकम्_pixel(desc),
               av_pix_fmt_गणनम्_planes(i));
    }

    प्रत्यागम 0;
}
