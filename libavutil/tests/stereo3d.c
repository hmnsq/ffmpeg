/*
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

#ಅನ್ತರ್ಭಾವ "libavutil/frame.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/stereo3d.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVStereo3D *s3d;
    AVFrame *ಚೌಕಟ್ಟು;
    size_t ಗಾತ್ರ_2;
    ಪೂರ್ಣಾಂಕ ret;

    /* av_stereo3d_alloc_size with size output */
    ಬರೆ("Testing av_stereo3d_alloc_size()\n");
    s3d = av_stereo3d_alloc_ಗಾತ್ರ(&ಗಾತ್ರ_2);
    ಬರೆ("alloc_size: %s, size>0: %s\n",
           s3d ? "OK" : "FAIL", ಗಾತ್ರ_2 > 0 ? "yes" : "no");
    av_free(s3d);

    /* av_stereo3d_alloc (no size) */
    s3d = av_stereo3d_alloc();
    ಬರೆ("alloc: %s\n", s3d ? "OK" : "FAIL");
    av_free(s3d);

    /* av_stereo3d_create_side_data */
    ಬರೆ("\nTesting av_stereo3d_create_side_data()\n");
    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    s3d = av_stereo3d_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
    ಬರೆ("create_side_data: %s\n", s3d ? "OK" : "FAIL");
    av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);

    /* av_stereo3d_type_name - all valid types */
    ಬರೆ("\nTesting av_stereo3d_type_name()\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i <= AV_STEREO3D_UNSPEC; i++)
        ಬರೆ("type %d: %s\n", i, av_stereo3d_type_name(i));
    ಬರೆ("out of range: %s\n", av_stereo3d_type_name(100));

    /* av_stereo3d_from_name - all valid names and unknown */
    ಬರೆ("\nTesting av_stereo3d_from_name()\n");
    {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ ಹೆಸರುಗಳು[] = {
            "2D", "side by side", "top and bottom", "frame alternate",
            "checkerboard", "side by side (quincunx subsampling)",
            "interleaved lines", "interleaved columns", "unspecified",
        };
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(ಹೆಸರುಗಳು); i++)
            ಬರೆ("%s: %d\n", ಹೆಸರುಗಳು[i], av_stereo3d_from_name(ಹೆಸರುಗಳು[i]));
    }
    ret = av_stereo3d_from_name("nonexistent");
    ಬರೆ("nonexistent: %d\n", ret);

    /* av_stereo3d_type_name / av_stereo3d_from_name round-trip */
    ಬರೆ("\nTesting type name round-trip\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i <= AV_STEREO3D_UNSPEC; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_stereo3d_type_name(i);
        ಪೂರ್ಣಾಂಕ rt = av_stereo3d_from_name(name);
        ಬರೆ("type roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_name - all valid views */
    ಬರೆ("\nTesting av_stereo3d_view_name()\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++)
        ಬರೆ("view %d: %s\n", i, av_stereo3d_view_name(i));
    ಬರೆ("out of range: %s\n", av_stereo3d_view_name(100));

    /* av_stereo3d_view_name / av_stereo3d_view_from_name round-trip */
    ಬರೆ("\nTesting view name round-trip\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_stereo3d_view_name(i);
        ಪೂರ್ಣಾಂಕ rt = av_stereo3d_view_from_name(name);
        ಬರೆ("view roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_from_name */
    ಬರೆ("\nTesting av_stereo3d_view_from_name()\n");
    ಬರೆ("packed: %d\n", av_stereo3d_view_from_name("packed"));
    ಬರೆ("left: %d\n", av_stereo3d_view_from_name("left"));
    ಬರೆ("right: %d\n", av_stereo3d_view_from_name("right"));
    ಬರೆ("unspecified: %d\n", av_stereo3d_view_from_name("unspecified"));
    ret = av_stereo3d_view_from_name("nonexistent");
    ಬರೆ("nonexistent: %d\n", ret);

    /* av_stereo3d_primary_eye_name - all valid values */
    ಬರೆ("\nTesting av_stereo3d_primary_eye_name()\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i <= AV_PRIMARY_EYE_ಬಲ; i++)
        ಬರೆ("eye %d: %s\n", i, av_stereo3d_primary_eye_name(i));
    ಬರೆ("out of range: %s\n", av_stereo3d_primary_eye_name(100));

    /* av_stereo3d_primary_eye_from_name */
    ಬರೆ("\nTesting av_stereo3d_primary_eye_from_name()\n");
    ಬರೆ("none: %d\n", av_stereo3d_primary_eye_from_name("none"));
    ಬರೆ("left: %d\n", av_stereo3d_primary_eye_from_name("left"));
    ಬರೆ("right: %d\n", av_stereo3d_primary_eye_from_name("right"));
    ret = av_stereo3d_primary_eye_from_name("nonexistent");
    ಬರೆ("nonexistent: %d\n", ret);

    ಹಿಂತಿರುಗಿ 0;
}
