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

#ضمن <stdio.h>

#ضمن "libavutil/frame.h"
#ضمن "libavutil/macros.h"
#ضمن "libavutil/mem.h"
#ضمن "libavutil/stereo3d.h"

صحيح اصلي(فراغ)
{
    AVStereo3D *s3d;
    AVFrame *چوکاټ;
    size_t اندازه;
    صحيح ret;

    /* av_stereo3d_alloc_size with size output */
    چاپ_کړه("Testing av_stereo3d_alloc_size()\n");
    s3d = av_stereo3d_alloc_اندازه(&اندازه);
    چاپ_کړه("alloc_size: %s, size>0: %s\n",
           s3d ? "OK" : "FAIL", اندازه > 0 ? "yes" : "no");
    av_free(s3d);

    /* av_stereo3d_alloc (no size) */
    s3d = av_stereo3d_alloc();
    چاپ_کړه("alloc: %s\n", s3d ? "OK" : "FAIL");
    av_free(s3d);

    /* av_stereo3d_create_side_data */
    چاپ_کړه("\nTesting av_stereo3d_create_side_data()\n");
    چوکاټ = av_چوکاټ_alloc();
    s3d = av_stereo3d_create_side_معلومات(چوکاټ);
    چاپ_کړه("create_side_data: %s\n", s3d ? "OK" : "FAIL");
    av_چوکاټ_free(&چوکاټ);

    /* av_stereo3d_type_name - all valid types */
    چاپ_کړه("\nTesting av_stereo3d_type_name()\n");
    لكل (صحيح i = 0; i <= AV_STEREO3D_UNSPEC; i++)
        چاپ_کړه("type %d: %s\n", i, av_stereo3d_type_name(i));
    چاپ_کړه("out of range: %s\n", av_stereo3d_type_name(100));

    /* av_stereo3d_from_name - all valid names and unknown */
    چاپ_کړه("\nTesting av_stereo3d_from_name()\n");
    {
        ساكن ثابت حرف * ثابت نومونه[] = {
            "2D", "side by side", "top and bottom", "frame alternate",
            "checkerboard", "side by side (quincunx subsampling)",
            "interleaved lines", "interleaved columns", "unspecified",
        };
        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(نومونه); i++)
            چاپ_کړه("%s: %d\n", نومونه[i], av_stereo3d_from_name(نومونه[i]));
    }
    ret = av_stereo3d_from_name("nonexistent");
    چاپ_کړه("nonexistent: %d\n", ret);

    /* av_stereo3d_type_name / av_stereo3d_from_name round-trip */
    چاپ_کړه("\nTesting type name round-trip\n");
    لكل (صحيح i = 0; i <= AV_STEREO3D_UNSPEC; i++) {
        ثابت حرف *name = av_stereo3d_type_name(i);
        صحيح rt = av_stereo3d_from_name(name);
        چاپ_کړه("type roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_name - all valid views */
    چاپ_کړه("\nTesting av_stereo3d_view_name()\n");
    لكل (صحيح i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++)
        چاپ_کړه("view %d: %s\n", i, av_stereo3d_view_name(i));
    چاپ_کړه("out of range: %s\n", av_stereo3d_view_name(100));

    /* av_stereo3d_view_name / av_stereo3d_view_from_name round-trip */
    چاپ_کړه("\nTesting view name round-trip\n");
    لكل (صحيح i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++) {
        ثابت حرف *name = av_stereo3d_view_name(i);
        صحيح rt = av_stereo3d_view_from_name(name);
        چاپ_کړه("view roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_from_name */
    چاپ_کړه("\nTesting av_stereo3d_view_from_name()\n");
    چاپ_کړه("packed: %d\n", av_stereo3d_view_from_name("packed"));
    چاپ_کړه("left: %d\n", av_stereo3d_view_from_name("left"));
    چاپ_کړه("right: %d\n", av_stereo3d_view_from_name("right"));
    چاپ_کړه("unspecified: %d\n", av_stereo3d_view_from_name("unspecified"));
    ret = av_stereo3d_view_from_name("nonexistent");
    چاپ_کړه("nonexistent: %d\n", ret);

    /* av_stereo3d_primary_eye_name - all valid values */
    چاپ_کړه("\nTesting av_stereo3d_primary_eye_name()\n");
    لكل (صحيح i = 0; i <= AV_PRIMARY_EYE_ښی; i++)
        چاپ_کړه("eye %d: %s\n", i, av_stereo3d_primary_eye_name(i));
    چاپ_کړه("out of range: %s\n", av_stereo3d_primary_eye_name(100));

    /* av_stereo3d_primary_eye_from_name */
    چاپ_کړه("\nTesting av_stereo3d_primary_eye_from_name()\n");
    چاپ_کړه("none: %d\n", av_stereo3d_primary_eye_from_name("none"));
    چاپ_کړه("left: %d\n", av_stereo3d_primary_eye_from_name("left"));
    چاپ_کړه("right: %d\n", av_stereo3d_primary_eye_from_name("right"));
    ret = av_stereo3d_primary_eye_from_name("nonexistent");
    چاپ_کړه("nonexistent: %d\n", ret);

    أرجع 0;
}
