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

#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "libavutil/macros.h"
#அந்தர்பாவ "libavutil/pixdesc.h"
#அந்தர்பாவ "libavutil/pixfmt.h"

/*
 * from_name() may legitimately map to a different index when two enum
 * values share the same name string (e.g. AVCOL_PRI_RESERVED0 and
 * AVCOL_PRI_RESERVED both use "reserved"). Accept that as long as
 * name(back) equals name(i).
 */
நிலையான முழு check_name_equivalence(மாறிலி எழுத்து *name, மாறிலி எழுத்து *back_name)
{
    திரும்பு back_name && !strcmp(name, back_name);
}

நிலையான முழு test_pix_fmt_round_trip(வெறுமை)
{
    முழு fail = 0;
    க்கு (முழு i = 0; i < AV_PIX_FMT_NB; i++) {
        மாறிலி எழுத்து *name = av_get_pix_fmt_name(i);
        எனில் (!name)
            தொடர்;
        எனில் (av_get_pix_fmt(name) != i)
            fail++;
    }
    திரும்பு fail;
}

நிலையான முழு test_color_range_round_trip(வெறுமை)
{
    முழு fail = 0;
    க்கு (முழு i = 0; i < AVCOL_RANGE_NB; i++) {
        மாறிலி எழுத்து *name = av_color_range_name(i);
        எனில் (!name)
            தொடர்;
        முழு back = av_color_range_from_name(name);
        எனில் (back < 0 || !check_name_equivalence(name, av_color_range_name(back)))
            fail++;
    }
    திரும்பு fail;
}

நிலையான முழு test_color_primaries_round_trip(வெறுமை)
{
    முழு fail = 0;
    க்கு (முழு i = 0; i < AVCOL_PRI_NB; i++) {
        மாறிலி எழுத்து *name = av_color_primaries_name(i);
        எனில் (!name)
            தொடர்;
        முழு back = av_color_primaries_from_name(name);
        எனில் (back < 0 || !check_name_equivalence(name, av_color_primaries_name(back)))
            fail++;
    }
    திரும்பு fail;
}

நிலையான முழு test_color_transfer_round_trip(வெறுமை)
{
    முழு fail = 0;
    க்கு (முழு i = 0; i < AVCOL_TRC_NB; i++) {
        மாறிலி எழுத்து *name = av_color_transfer_name(i);
        எனில் (!name)
            தொடர்;
        முழு back = av_color_transfer_from_name(name);
        எனில் (back < 0 || !check_name_equivalence(name, av_color_transfer_name(back)))
            fail++;
    }
    திரும்பு fail;
}

நிலையான முழு test_color_space_round_trip(வெறுமை)
{
    முழு fail = 0;
    க்கு (முழு i = 0; i < AVCOL_SPC_NB; i++) {
        மாறிலி எழுத்து *name = av_color_space_name(i);
        எனில் (!name)
            தொடர்;
        முழு back = av_color_space_from_name(name);
        எனில் (back < 0 || !check_name_equivalence(name, av_color_space_name(back)))
            fail++;
    }
    திரும்பு fail;
}

நிலையான முழு test_chroma_location_round_trip(வெறுமை)
{
    முழு fail = 0;
    க்கு (முழு i = 0; i < AVCHROMA_LOC_NB; i++) {
        மாறிலி எழுத்து *name = av_chroma_location_name(i);
        எனில் (!name)
            தொடர்;
        முழு back = av_chroma_location_from_name(name);
        எனில் (back < 0 || !check_name_equivalence(name, av_chroma_location_name(back)))
            fail++;
    }
    திரும்பு fail;
}

நிலையான முழு test_alpha_mode_round_trip(வெறுமை)
{
    முழு fail = 0;
    க்கு (முழு i = 0; i < AVALPHA_MODE_NB; i++) {
        மாறிலி எழுத்து *name = av_alpha_mode_name(i);
        எனில் (!name)
            தொடர்;
        முழு back = av_alpha_mode_from_name(name);
        எனில் (back < 0 || !check_name_equivalence(name, av_alpha_mode_name(back)))
            fail++;
    }
    திரும்பு fail;
}

நிலையான முழு test_chroma_location_pos_round_trip(வெறுமை)
{
    முழு fail = 0;
    க்கு (முழு i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        முழு xpos, ypos;
        எனில் (av_chroma_location_enum_to_pos(&xpos, &ypos, i) < 0) {
            fail++;
            தொடர்;
        }
        எனில் ((முழு)av_chroma_location_pos_to_enum(xpos, ypos) != i)
            fail++;
    }
    திரும்பு fail;
}

முழு முதன்மை(வெறுமை)
{
    முழு skip = 0;

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
    க்கு (முழு i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        எனில் (!desc || !desc->name) {
            skip++;
            தொடர்;
        }
        எனில் (skip) {
            printf("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        printf("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_bits_per_pixel(desc),
               av_pix_fmt_மொத்தம்_planes(i));
    }

    திரும்பு 0;
}
