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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixdesc.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixfmt.h"

/*
 * from_name() may legitimately map to a different index when two enum
 * values share the same name string (e.g. AVCOL_PRI_RESERVED0 and
 * AVCOL_PRI_RESERVED both use "reserved"). Accept that as long as
 * name(back) equals name(i).
 */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ check_name_equivalence(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಹಿಂಭಾಗ_name)
{
    ಹಿಂತಿರುಗಿ ಹಿಂಭಾಗ_name && !strcmp(name, ಹಿಂಭಾಗ_name);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_pix_fmt_ಸುತ್ತು_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ fail = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AV_PIX_FMT_NB; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_get_pix_fmt_name(i);
        ಆದರೆ (!name)
            ಮುಂದುವರಿ;
        ಆದರೆ (av_get_pix_fmt(name) != i)
            fail++;
    }
    ಹಿಂತಿರುಗಿ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_color_range_ಸುತ್ತು_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ fail = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AVCOL_RANGE_NB; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_color_range_name(i);
        ಆದರೆ (!name)
            ಮುಂದುವರಿ;
        ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ = av_color_range_from_name(name);
        ಆದರೆ (ಹಿಂಭಾಗ < 0 || !check_name_equivalence(name, av_color_range_name(ಹಿಂಭಾಗ)))
            fail++;
    }
    ಹಿಂತಿರುಗಿ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_color_primaries_ಸುತ್ತು_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ fail = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AVCOL_PRI_NB; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_color_primaries_name(i);
        ಆದರೆ (!name)
            ಮುಂದುವರಿ;
        ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ = av_color_primaries_from_name(name);
        ಆದರೆ (ಹಿಂಭಾಗ < 0 || !check_name_equivalence(name, av_color_primaries_name(ಹಿಂಭಾಗ)))
            fail++;
    }
    ಹಿಂತಿರುಗಿ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_color_transfer_ಸುತ್ತು_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ fail = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AVCOL_TRC_NB; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_color_transfer_name(i);
        ಆದರೆ (!name)
            ಮುಂದುವರಿ;
        ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ = av_color_transfer_from_name(name);
        ಆದರೆ (ಹಿಂಭಾಗ < 0 || !check_name_equivalence(name, av_color_transfer_name(ಹಿಂಭಾಗ)))
            fail++;
    }
    ಹಿಂತಿರುಗಿ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_color_space_ಸುತ್ತು_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ fail = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AVCOL_SPC_NB; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_color_space_name(i);
        ಆದರೆ (!name)
            ಮುಂದುವರಿ;
        ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ = av_color_space_from_name(name);
        ಆದರೆ (ಹಿಂಭಾಗ < 0 || !check_name_equivalence(name, av_color_space_name(ಹಿಂಭಾಗ)))
            fail++;
    }
    ಹಿಂತಿರುಗಿ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_chroma_location_ಸುತ್ತು_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ fail = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AVCHROMA_LOC_NB; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_chroma_location_name(i);
        ಆದರೆ (!name)
            ಮುಂದುವರಿ;
        ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ = av_chroma_location_from_name(name);
        ಆದರೆ (ಹಿಂಭಾಗ < 0 || !check_name_equivalence(name, av_chroma_location_name(ಹಿಂಭಾಗ)))
            fail++;
    }
    ಹಿಂತಿರುಗಿ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_alpha_ಬಹುಲಕ_ಸುತ್ತು_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ fail = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AVALPHA_ಬಹುಲಕ_NB; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_alpha_ಬಹುಲಕ_name(i);
        ಆದರೆ (!name)
            ಮುಂದುವರಿ;
        ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ = av_alpha_ಬಹುಲಕ_from_name(name);
        ಆದರೆ (ಹಿಂಭಾಗ < 0 || !check_name_equivalence(name, av_alpha_ಬಹುಲಕ_name(ಹಿಂಭಾಗ)))
            fail++;
    }
    ಹಿಂತಿರುಗಿ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_chroma_location_pos_ಸುತ್ತು_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ fail = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        ಪೂರ್ಣಾಂಕ xpos, ypos;
        ಆದರೆ (av_chroma_location_enum_ಗಮ್ಯ_pos(&xpos, &ypos, i) < 0) {
            fail++;
            ಮುಂದುವರಿ;
        }
        ಆದರೆ ((ಪೂರ್ಣಾಂಕ)av_chroma_location_pos_ಗಮ್ಯ_enum(xpos, ypos) != i)
            fail++;
    }
    ಹಿಂತಿರುಗಿ fail;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ skip = 0;

    ಬರೆ("Testing av_get_pix_fmt() / av_get_pix_fmt_name() round-trip\n");
    ಬರೆ("  result: %s\n",
           test_pix_fmt_ಸುತ್ತು_trip() ? "FAIL" : "OK");

    ಬರೆ("\nTesting av_color_*_name() / av_color_*_from_name() round-trips\n");
    ಬರೆ("  av_color_range:     %s\n",
           test_color_range_ಸುತ್ತು_trip()     ? "FAIL" : "OK");
    ಬರೆ("  av_color_primaries: %s\n",
           test_color_primaries_ಸುತ್ತು_trip() ? "FAIL" : "OK");
    ಬರೆ("  av_color_transfer:  %s\n",
           test_color_transfer_ಸುತ್ತು_trip()  ? "FAIL" : "OK");
    ಬರೆ("  av_color_space:     %s\n",
           test_color_space_ಸುತ್ತು_trip()     ? "FAIL" : "OK");
    ಬರೆ("  av_chroma_location: %s\n",
           test_chroma_location_ಸುತ್ತು_trip() ? "FAIL" : "OK");
    ಬರೆ("  av_alpha_mode:      %s\n",
           test_alpha_ಬಹುಲಕ_ಸುತ್ತು_trip()      ? "FAIL" : "OK");

    ಬರೆ("\nTesting av_chroma_location_enum_to_pos / pos_to_enum round-trip\n");
    ಬರೆ("  result: %s\n",
           test_chroma_location_pos_ಸುತ್ತು_trip() ? "FAIL" : "OK");

    ಬರೆ("\nTesting pixel format descriptors\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        ಆದರೆ (!desc || !desc->name) {
            skip++;
            ಮುಂದುವರಿ;
        }
        ಆದರೆ (skip) {
            ಬರೆ("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        ಬರೆ("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel(desc),
               av_pix_fmt_ಎಣಿಕೆ_planes(i));
    }

    ಹಿಂತಿರುಗಿ 0;
}
