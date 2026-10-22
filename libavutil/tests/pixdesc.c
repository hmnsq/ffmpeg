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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixfmt.h"

/*
 * from_name() may legitimately map to a different index when two enum
 * values share the same name string (e.g. AVCOL_PRI_RESERVED0 and
 * AVCOL_PRI_RESERVED both use "reserved"). Accept that as long as
 * name(back) equals name(i).
 */
ਸਥਿਰ ਪੂਰਨ check_name_equivalence(ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *ਪਿੱਠ_name)
{
    ਵਾਪਸ ਪਿੱਠ_name && !strcmp(name, ਪਿੱਠ_name);
}

ਸਥਿਰ ਪੂਰਨ test_pix_fmt_ਗੇੜਾ_trip(ਖਾਲੀ)
{
    ਪੂਰਨ fail = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < AV_PIX_FMT_NB; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_get_pix_fmt_name(i);
        ਜੇ (!name)
            ਜਾਰੀ;
        ਜੇ (av_get_pix_fmt(name) != i)
            fail++;
    }
    ਵਾਪਸ fail;
}

ਸਥਿਰ ਪੂਰਨ test_color_range_ਗੇੜਾ_trip(ਖਾਲੀ)
{
    ਪੂਰਨ fail = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < AVCOL_RANGE_NB; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_color_range_name(i);
        ਜੇ (!name)
            ਜਾਰੀ;
        ਪੂਰਨ ਪਿੱਠ = av_color_range_from_name(name);
        ਜੇ (ਪਿੱਠ < 0 || !check_name_equivalence(name, av_color_range_name(ਪਿੱਠ)))
            fail++;
    }
    ਵਾਪਸ fail;
}

ਸਥਿਰ ਪੂਰਨ test_color_primaries_ਗੇੜਾ_trip(ਖਾਲੀ)
{
    ਪੂਰਨ fail = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < AVCOL_PRI_NB; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_color_primaries_name(i);
        ਜੇ (!name)
            ਜਾਰੀ;
        ਪੂਰਨ ਪਿੱਠ = av_color_primaries_from_name(name);
        ਜੇ (ਪਿੱਠ < 0 || !check_name_equivalence(name, av_color_primaries_name(ਪਿੱਠ)))
            fail++;
    }
    ਵਾਪਸ fail;
}

ਸਥਿਰ ਪੂਰਨ test_color_transfer_ਗੇੜਾ_trip(ਖਾਲੀ)
{
    ਪੂਰਨ fail = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < AVCOL_TRC_NB; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_color_transfer_name(i);
        ਜੇ (!name)
            ਜਾਰੀ;
        ਪੂਰਨ ਪਿੱਠ = av_color_transfer_from_name(name);
        ਜੇ (ਪਿੱਠ < 0 || !check_name_equivalence(name, av_color_transfer_name(ਪਿੱਠ)))
            fail++;
    }
    ਵਾਪਸ fail;
}

ਸਥਿਰ ਪੂਰਨ test_color_space_ਗੇੜਾ_trip(ਖਾਲੀ)
{
    ਪੂਰਨ fail = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < AVCOL_SPC_NB; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_color_space_name(i);
        ਜੇ (!name)
            ਜਾਰੀ;
        ਪੂਰਨ ਪਿੱਠ = av_color_space_from_name(name);
        ਜੇ (ਪਿੱਠ < 0 || !check_name_equivalence(name, av_color_space_name(ਪਿੱਠ)))
            fail++;
    }
    ਵਾਪਸ fail;
}

ਸਥਿਰ ਪੂਰਨ test_chroma_location_ਗੇੜਾ_trip(ਖਾਲੀ)
{
    ਪੂਰਨ fail = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < AVCHROMA_LOC_NB; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_chroma_location_name(i);
        ਜੇ (!name)
            ਜਾਰੀ;
        ਪੂਰਨ ਪਿੱਠ = av_chroma_location_from_name(name);
        ਜੇ (ਪਿੱਠ < 0 || !check_name_equivalence(name, av_chroma_location_name(ਪਿੱਠ)))
            fail++;
    }
    ਵਾਪਸ fail;
}

ਸਥਿਰ ਪੂਰਨ test_alpha_ਬਹੁਲਕ_ਗੇੜਾ_trip(ਖਾਲੀ)
{
    ਪੂਰਨ fail = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < AVALPHA_ਬਹੁਲਕ_NB; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_alpha_ਬਹੁਲਕ_name(i);
        ਜੇ (!name)
            ਜਾਰੀ;
        ਪੂਰਨ ਪਿੱਠ = av_alpha_ਬਹੁਲਕ_from_name(name);
        ਜੇ (ਪਿੱਠ < 0 || !check_name_equivalence(name, av_alpha_ਬਹੁਲਕ_name(ਪਿੱਠ)))
            fail++;
    }
    ਵਾਪਸ fail;
}

ਸਥਿਰ ਪੂਰਨ test_chroma_location_pos_ਗੇੜਾ_trip(ਖਾਲੀ)
{
    ਪੂਰਨ fail = 0;
    ਲਈ (ਪੂਰਨ i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        ਪੂਰਨ xpos, ypos;
        ਜੇ (av_chroma_location_enum_ਮੰਜ਼ਿਲ_pos(&xpos, &ypos, i) < 0) {
            fail++;
            ਜਾਰੀ;
        }
        ਜੇ ((ਪੂਰਨ)av_chroma_location_pos_ਮੰਜ਼ਿਲ_enum(xpos, ypos) != i)
            fail++;
    }
    ਵਾਪਸ fail;
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਪੂਰਨ skip = 0;

    ਲਿਖੋ("Testing av_get_pix_fmt() / av_get_pix_fmt_name() round-trip\n");
    ਲਿਖੋ("  result: %s\n",
           test_pix_fmt_ਗੇੜਾ_trip() ? "FAIL" : "OK");

    ਲਿਖੋ("\nTesting av_color_*_name() / av_color_*_from_name() round-trips\n");
    ਲਿਖੋ("  av_color_range:     %s\n",
           test_color_range_ਗੇੜਾ_trip()     ? "FAIL" : "OK");
    ਲਿਖੋ("  av_color_primaries: %s\n",
           test_color_primaries_ਗੇੜਾ_trip() ? "FAIL" : "OK");
    ਲਿਖੋ("  av_color_transfer:  %s\n",
           test_color_transfer_ਗੇੜਾ_trip()  ? "FAIL" : "OK");
    ਲਿਖੋ("  av_color_space:     %s\n",
           test_color_space_ਗੇੜਾ_trip()     ? "FAIL" : "OK");
    ਲਿਖੋ("  av_chroma_location: %s\n",
           test_chroma_location_ਗੇੜਾ_trip() ? "FAIL" : "OK");
    ਲਿਖੋ("  av_alpha_mode:      %s\n",
           test_alpha_ਬਹੁਲਕ_ਗੇੜਾ_trip()      ? "FAIL" : "OK");

    ਲਿਖੋ("\nTesting av_chroma_location_enum_to_pos / pos_to_enum round-trip\n");
    ਲਿਖੋ("  result: %s\n",
           test_chroma_location_pos_ਗੇੜਾ_trip() ? "FAIL" : "OK");

    ਲਿਖੋ("\nTesting pixel format descriptors\n");
    ਲਈ (ਪੂਰਨ i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        ਜੇ (!desc || !desc->name) {
            skip++;
            ਜਾਰੀ;
        }
        ਜੇ (skip) {
            ਲਿਖੋ("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        ਲਿਖੋ("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_ਬਿੱਟ_ਪ੍ਰਤੀ_pixel(desc),
               av_pix_fmt_ਗਿਣਤੀ_planes(i));
    }

    ਵਾਪਸ 0;
}
