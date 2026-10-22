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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/stereo3d.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVStereo3D *s3d;
    AVFrame *ਚੌਖਟਾ;
    size_t ਮਾਪ;
    ਪੂਰਨ ret;

    /* av_stereo3d_alloc_size with size output */
    ਲਿਖੋ("Testing av_stereo3d_alloc_size()\n");
    s3d = av_stereo3d_alloc_ਮਾਪ(&ਮਾਪ);
    ਲਿਖੋ("alloc_size: %s, size>0: %s\n",
           s3d ? "OK" : "FAIL", ਮਾਪ > 0 ? "yes" : "no");
    av_free(s3d);

    /* av_stereo3d_alloc (no size) */
    s3d = av_stereo3d_alloc();
    ਲਿਖੋ("alloc: %s\n", s3d ? "OK" : "FAIL");
    av_free(s3d);

    /* av_stereo3d_create_side_data */
    ਲਿਖੋ("\nTesting av_stereo3d_create_side_data()\n");
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    s3d = av_stereo3d_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
    ਲਿਖੋ("create_side_data: %s\n", s3d ? "OK" : "FAIL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* av_stereo3d_type_name - all valid types */
    ਲਿਖੋ("\nTesting av_stereo3d_type_name()\n");
    ਲਈ (ਪੂਰਨ i = 0; i <= AV_STEREO3D_UNSPEC; i++)
        ਲਿਖੋ("type %d: %s\n", i, av_stereo3d_type_name(i));
    ਲਿਖੋ("out of range: %s\n", av_stereo3d_type_name(100));

    /* av_stereo3d_from_name - all valid names and unknown */
    ਲਿਖੋ("\nTesting av_stereo3d_from_name()\n");
    {
        ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ ਨਾਂ[] = {
            "2D", "side by side", "top and bottom", "frame alternate",
            "checkerboard", "side by side (quincunx subsampling)",
            "interleaved lines", "interleaved columns", "unspecified",
        };
        ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(ਨਾਂ); i++)
            ਲਿਖੋ("%s: %d\n", ਨਾਂ[i], av_stereo3d_from_name(ਨਾਂ[i]));
    }
    ret = av_stereo3d_from_name("nonexistent");
    ਲਿਖੋ("nonexistent: %d\n", ret);

    /* av_stereo3d_type_name / av_stereo3d_from_name round-trip */
    ਲਿਖੋ("\nTesting type name round-trip\n");
    ਲਈ (ਪੂਰਨ i = 0; i <= AV_STEREO3D_UNSPEC; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_stereo3d_type_name(i);
        ਪੂਰਨ rt = av_stereo3d_from_name(name);
        ਲਿਖੋ("type roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_name - all valid views */
    ਲਿਖੋ("\nTesting av_stereo3d_view_name()\n");
    ਲਈ (ਪੂਰਨ i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++)
        ਲਿਖੋ("view %d: %s\n", i, av_stereo3d_view_name(i));
    ਲਿਖੋ("out of range: %s\n", av_stereo3d_view_name(100));

    /* av_stereo3d_view_name / av_stereo3d_view_from_name round-trip */
    ਲਿਖੋ("\nTesting view name round-trip\n");
    ਲਈ (ਪੂਰਨ i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_stereo3d_view_name(i);
        ਪੂਰਨ rt = av_stereo3d_view_from_name(name);
        ਲਿਖੋ("view roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_from_name */
    ਲਿਖੋ("\nTesting av_stereo3d_view_from_name()\n");
    ਲਿਖੋ("packed: %d\n", av_stereo3d_view_from_name("packed"));
    ਲਿਖੋ("left: %d\n", av_stereo3d_view_from_name("left"));
    ਲਿਖੋ("right: %d\n", av_stereo3d_view_from_name("right"));
    ਲਿਖੋ("unspecified: %d\n", av_stereo3d_view_from_name("unspecified"));
    ret = av_stereo3d_view_from_name("nonexistent");
    ਲਿਖੋ("nonexistent: %d\n", ret);

    /* av_stereo3d_primary_eye_name - all valid values */
    ਲਿਖੋ("\nTesting av_stereo3d_primary_eye_name()\n");
    ਲਈ (ਪੂਰਨ i = 0; i <= AV_PRIMARY_EYE_ਸੱਜਾ; i++)
        ਲਿਖੋ("eye %d: %s\n", i, av_stereo3d_primary_eye_name(i));
    ਲਿਖੋ("out of range: %s\n", av_stereo3d_primary_eye_name(100));

    /* av_stereo3d_primary_eye_from_name */
    ਲਿਖੋ("\nTesting av_stereo3d_primary_eye_from_name()\n");
    ਲਿਖੋ("none: %d\n", av_stereo3d_primary_eye_from_name("none"));
    ਲਿਖੋ("left: %d\n", av_stereo3d_primary_eye_from_name("left"));
    ਲਿਖੋ("right: %d\n", av_stereo3d_primary_eye_from_name("right"));
    ret = av_stereo3d_primary_eye_from_name("nonexistent");
    ਲਿਖੋ("nonexistent: %d\n", ret);

    ਵਾਪਸ 0;
}
