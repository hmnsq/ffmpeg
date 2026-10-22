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

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/macros.h"
#అన్తర్భావ "libavutil/pixdesc.h"
#అన్తర్భావ "libavutil/pixfmt.h"

/*
 * from_name() may legitimately map to a different index when two enum
 * values share the same name string (e.g. AVCOL_PRI_RESERVED0 and
 * AVCOL_PRI_RESERVED both use "reserved"). Accept that as long as
 * name(back) equals name(i).
 */
స్థిర పూర్ణాంకం check_name_equivalence(స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *వెనుక_name)
{
    తిరిగి వెనుక_name && !strcmp(name, వెనుక_name);
}

స్థిర పూర్ణాంకం test_pix_fmt_విడత_trip(శూన్య)
{
    పూర్ణాంకం fail = 0;
    కొరకు (పూర్ణాంకం i = 0; i < AV_PIX_FMT_NB; i++) {
        స్థిరరాశి అక్షరం *name = av_get_pix_fmt_name(i);
        ఒకవేళ (!name)
            కొనసాగు;
        ఒకవేళ (av_get_pix_fmt(name) != i)
            fail++;
    }
    తిరిగి fail;
}

స్థిర పూర్ణాంకం test_color_range_విడత_trip(శూన్య)
{
    పూర్ణాంకం fail = 0;
    కొరకు (పూర్ణాంకం i = 0; i < AVCOL_RANGE_NB; i++) {
        స్థిరరాశి అక్షరం *name = av_color_range_name(i);
        ఒకవేళ (!name)
            కొనసాగు;
        పూర్ణాంకం వెనుక = av_color_range_from_name(name);
        ఒకవేళ (వెనుక < 0 || !check_name_equivalence(name, av_color_range_name(వెనుక)))
            fail++;
    }
    తిరిగి fail;
}

స్థిర పూర్ణాంకం test_color_primaries_విడత_trip(శూన్య)
{
    పూర్ణాంకం fail = 0;
    కొరకు (పూర్ణాంకం i = 0; i < AVCOL_PRI_NB; i++) {
        స్థిరరాశి అక్షరం *name = av_color_primaries_name(i);
        ఒకవేళ (!name)
            కొనసాగు;
        పూర్ణాంకం వెనుక = av_color_primaries_from_name(name);
        ఒకవేళ (వెనుక < 0 || !check_name_equivalence(name, av_color_primaries_name(వెనుక)))
            fail++;
    }
    తిరిగి fail;
}

స్థిర పూర్ణాంకం test_color_transfer_విడత_trip(శూన్య)
{
    పూర్ణాంకం fail = 0;
    కొరకు (పూర్ణాంకం i = 0; i < AVCOL_TRC_NB; i++) {
        స్థిరరాశి అక్షరం *name = av_color_transfer_name(i);
        ఒకవేళ (!name)
            కొనసాగు;
        పూర్ణాంకం వెనుక = av_color_transfer_from_name(name);
        ఒకవేళ (వెనుక < 0 || !check_name_equivalence(name, av_color_transfer_name(వెనుక)))
            fail++;
    }
    తిరిగి fail;
}

స్థిర పూర్ణాంకం test_color_space_విడత_trip(శూన్య)
{
    పూర్ణాంకం fail = 0;
    కొరకు (పూర్ణాంకం i = 0; i < AVCOL_SPC_NB; i++) {
        స్థిరరాశి అక్షరం *name = av_color_space_name(i);
        ఒకవేళ (!name)
            కొనసాగు;
        పూర్ణాంకం వెనుక = av_color_space_from_name(name);
        ఒకవేళ (వెనుక < 0 || !check_name_equivalence(name, av_color_space_name(వెనుక)))
            fail++;
    }
    తిరిగి fail;
}

స్థిర పూర్ణాంకం test_chroma_location_విడత_trip(శూన్య)
{
    పూర్ణాంకం fail = 0;
    కొరకు (పూర్ణాంకం i = 0; i < AVCHROMA_LOC_NB; i++) {
        స్థిరరాశి అక్షరం *name = av_chroma_location_name(i);
        ఒకవేళ (!name)
            కొనసాగు;
        పూర్ణాంకం వెనుక = av_chroma_location_from_name(name);
        ఒకవేళ (వెనుక < 0 || !check_name_equivalence(name, av_chroma_location_name(వెనుక)))
            fail++;
    }
    తిరిగి fail;
}

స్థిర పూర్ణాంకం test_alpha_బహుళకం_విడత_trip(శూన్య)
{
    పూర్ణాంకం fail = 0;
    కొరకు (పూర్ణాంకం i = 0; i < AVALPHA_బహుళకం_NB; i++) {
        స్థిరరాశి అక్షరం *name = av_alpha_బహుళకం_name(i);
        ఒకవేళ (!name)
            కొనసాగు;
        పూర్ణాంకం వెనుక = av_alpha_బహుళకం_from_name(name);
        ఒకవేళ (వెనుక < 0 || !check_name_equivalence(name, av_alpha_బహుళకం_name(వెనుక)))
            fail++;
    }
    తిరిగి fail;
}

స్థిర పూర్ణాంకం test_chroma_location_pos_విడత_trip(శూన్య)
{
    పూర్ణాంకం fail = 0;
    కొరకు (పూర్ణాంకం i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        పూర్ణాంకం xpos, ypos;
        ఒకవేళ (av_chroma_location_enum_గమ్యం_pos(&xpos, &ypos, i) < 0) {
            fail++;
            కొనసాగు;
        }
        ఒకవేళ ((పూర్ణాంకం)av_chroma_location_pos_గమ్యం_enum(xpos, ypos) != i)
            fail++;
    }
    తిరిగి fail;
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    పూర్ణాంకం skip = 0;

    రాయి("Testing av_get_pix_fmt() / av_get_pix_fmt_name() round-trip\n");
    రాయి("  result: %s\n",
           test_pix_fmt_విడత_trip() ? "FAIL" : "OK");

    రాయి("\nTesting av_color_*_name() / av_color_*_from_name() round-trips\n");
    రాయి("  av_color_range:     %s\n",
           test_color_range_విడత_trip()     ? "FAIL" : "OK");
    రాయి("  av_color_primaries: %s\n",
           test_color_primaries_విడత_trip() ? "FAIL" : "OK");
    రాయి("  av_color_transfer:  %s\n",
           test_color_transfer_విడత_trip()  ? "FAIL" : "OK");
    రాయి("  av_color_space:     %s\n",
           test_color_space_విడత_trip()     ? "FAIL" : "OK");
    రాయి("  av_chroma_location: %s\n",
           test_chroma_location_విడత_trip() ? "FAIL" : "OK");
    రాయి("  av_alpha_mode:      %s\n",
           test_alpha_బహుళకం_విడత_trip()      ? "FAIL" : "OK");

    రాయి("\nTesting av_chroma_location_enum_to_pos / pos_to_enum round-trip\n");
    రాయి("  result: %s\n",
           test_chroma_location_pos_విడత_trip() ? "FAIL" : "OK");

    రాయి("\nTesting pixel format descriptors\n");
    కొరకు (పూర్ణాంకం i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        ఒకవేళ (!desc || !desc->name) {
            skip++;
            కొనసాగు;
        }
        ఒకవేళ (skip) {
            రాయి("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        రాయి("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_బిట్లు_చొప్పున_pixel(desc),
               av_pix_fmt_లెక్క_planes(i));
    }

    తిరిగి 0;
}
