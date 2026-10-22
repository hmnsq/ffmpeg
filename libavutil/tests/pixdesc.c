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
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ check_name_equivalence(ಧ್ರುವ ವರ್ಣ *name, ಧ್ರುವ ವರ್ಣ *back_name)
{
    ಪ್ರತ್ಯಾಗಮ back_name && !strcmp(name, back_name);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_pix_fmt_round_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ fail = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < AV_PIX_FMT_NB; i++) {
        ಧ್ರುವ ವರ್ಣ *name = av_get_pix_fmt_name(i);
        ಯದಿ (!name)
            ಅನುವರ್ತ;
        ಯದಿ (av_get_pix_fmt(name) != i)
            fail++;
    }
    ಪ್ರತ್ಯಾಗಮ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_color_range_round_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ fail = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < AVCOL_RANGE_NB; i++) {
        ಧ್ರುವ ವರ್ಣ *name = av_color_range_name(i);
        ಯದಿ (!name)
            ಅನುವರ್ತ;
        ಪೂರ್ಣಾಙ್ಕ back = av_color_range_from_name(name);
        ಯದಿ (back < 0 || !check_name_equivalence(name, av_color_range_name(back)))
            fail++;
    }
    ಪ್ರತ್ಯಾಗಮ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_color_primaries_round_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ fail = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < AVCOL_PRI_NB; i++) {
        ಧ್ರುವ ವರ್ಣ *name = av_color_primaries_name(i);
        ಯದಿ (!name)
            ಅನುವರ್ತ;
        ಪೂರ್ಣಾಙ್ಕ back = av_color_primaries_from_name(name);
        ಯದಿ (back < 0 || !check_name_equivalence(name, av_color_primaries_name(back)))
            fail++;
    }
    ಪ್ರತ್ಯಾಗಮ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_color_transfer_round_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ fail = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < AVCOL_TRC_NB; i++) {
        ಧ್ರುವ ವರ್ಣ *name = av_color_transfer_name(i);
        ಯದಿ (!name)
            ಅನುವರ್ತ;
        ಪೂರ್ಣಾಙ್ಕ back = av_color_transfer_from_name(name);
        ಯದಿ (back < 0 || !check_name_equivalence(name, av_color_transfer_name(back)))
            fail++;
    }
    ಪ್ರತ್ಯಾಗಮ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_color_space_round_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ fail = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < AVCOL_SPC_NB; i++) {
        ಧ್ರುವ ವರ್ಣ *name = av_color_space_name(i);
        ಯದಿ (!name)
            ಅನುವರ್ತ;
        ಪೂರ್ಣಾಙ್ಕ back = av_color_space_from_name(name);
        ಯದಿ (back < 0 || !check_name_equivalence(name, av_color_space_name(back)))
            fail++;
    }
    ಪ್ರತ್ಯಾಗಮ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_chroma_location_round_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ fail = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < AVCHROMA_LOC_NB; i++) {
        ಧ್ರುವ ವರ್ಣ *name = av_chroma_location_name(i);
        ಯದಿ (!name)
            ಅನುವರ್ತ;
        ಪೂರ್ಣಾಙ್ಕ back = av_chroma_location_from_name(name);
        ಯದಿ (back < 0 || !check_name_equivalence(name, av_chroma_location_name(back)))
            fail++;
    }
    ಪ್ರತ್ಯಾಗಮ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_alpha_mode_round_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ fail = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < AVALPHA_MODE_NB; i++) {
        ಧ್ರುವ ವರ್ಣ *name = av_alpha_mode_name(i);
        ಯದಿ (!name)
            ಅನುವರ್ತ;
        ಪೂರ್ಣಾಙ್ಕ back = av_alpha_mode_from_name(name);
        ಯದಿ (back < 0 || !check_name_equivalence(name, av_alpha_mode_name(back)))
            fail++;
    }
    ಪ್ರತ್ಯಾಗಮ fail;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_chroma_location_pos_round_trip(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ fail = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        ಪೂರ್ಣಾಙ್ಕ xpos, ypos;
        ಯದಿ (av_chroma_location_enum_to_pos(&xpos, &ypos, i) < 0) {
            fail++;
            ಅನುವರ್ತ;
        }
        ಯದಿ ((ಪೂರ್ಣಾಙ್ಕ)av_chroma_location_pos_to_enum(xpos, ypos) != i)
            fail++;
    }
    ಪ್ರತ್ಯಾಗಮ fail;
}

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ skip = 0;

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
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        ಯದಿ (!desc || !desc->name) {
            skip++;
            ಅನುವರ್ತ;
        }
        ಯದಿ (skip) {
            printf("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        printf("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_bits_per_pixel(desc),
               av_pix_fmt_ಎಣಿಕೆ_planes(i));
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
