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

#شامل <stdio.h>

#شامل "libavutil/frame.h"
#شامل "libavutil/macros.h"
#شامل "libavutil/mem.h"
#شامل "libavutil/stereo3d.h"

صحیح مین(خالی)
{
    AVStereo3D *s3d;
    AVFrame *چوکھٹا;
    size_t سائز;
    صحیح ret;

    /* av_stereo3d_alloc_size with size output */
    لکھو("Testing av_stereo3d_alloc_size()\n");
    s3d = av_stereo3d_alloc_سائز(&سائز);
    لکھو("alloc_size: %s, size>0: %s\n",
           s3d ? "OK" : "FAIL", سائز > 0 ? "yes" : "no");
    av_free(s3d);

    /* av_stereo3d_alloc (no size) */
    s3d = av_stereo3d_alloc();
    لکھو("alloc: %s\n", s3d ? "OK" : "FAIL");
    av_free(s3d);

    /* av_stereo3d_create_side_data */
    لکھو("\nTesting av_stereo3d_create_side_data()\n");
    چوکھٹا = av_چوکھٹا_alloc();
    s3d = av_stereo3d_create_side_ڈیٹا(چوکھٹا);
    لکھو("create_side_data: %s\n", s3d ? "OK" : "FAIL");
    av_چوکھٹا_free(&چوکھٹا);

    /* av_stereo3d_type_name - all valid types */
    لکھو("\nTesting av_stereo3d_type_name()\n");
    برائے (صحیح i = 0; i <= AV_STEREO3D_UNSPEC; i++)
        لکھو("type %d: %s\n", i, av_stereo3d_type_name(i));
    لکھو("out of range: %s\n", av_stereo3d_type_name(100));

    /* av_stereo3d_from_name - all valid names and unknown */
    لکھو("\nTesting av_stereo3d_from_name()\n");
    {
        ساکن ثابت حرف * ثابت نام[] = {
            "2D", "side by side", "top and bottom", "frame alternate",
            "checkerboard", "side by side (quincunx subsampling)",
            "interleaved lines", "interleaved columns", "unspecified",
        };
        برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(نام); i++)
            لکھو("%s: %d\n", نام[i], av_stereo3d_from_name(نام[i]));
    }
    ret = av_stereo3d_from_name("nonexistent");
    لکھو("nonexistent: %d\n", ret);

    /* av_stereo3d_type_name / av_stereo3d_from_name round-trip */
    لکھو("\nTesting type name round-trip\n");
    برائے (صحیح i = 0; i <= AV_STEREO3D_UNSPEC; i++) {
        ثابت حرف *name = av_stereo3d_type_name(i);
        صحیح rt = av_stereo3d_from_name(name);
        لکھو("type roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_name - all valid views */
    لکھو("\nTesting av_stereo3d_view_name()\n");
    برائے (صحیح i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++)
        لکھو("view %d: %s\n", i, av_stereo3d_view_name(i));
    لکھو("out of range: %s\n", av_stereo3d_view_name(100));

    /* av_stereo3d_view_name / av_stereo3d_view_from_name round-trip */
    لکھو("\nTesting view name round-trip\n");
    برائے (صحیح i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++) {
        ثابت حرف *name = av_stereo3d_view_name(i);
        صحیح rt = av_stereo3d_view_from_name(name);
        لکھو("view roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_from_name */
    لکھو("\nTesting av_stereo3d_view_from_name()\n");
    لکھو("packed: %d\n", av_stereo3d_view_from_name("packed"));
    لکھو("left: %d\n", av_stereo3d_view_from_name("left"));
    لکھو("right: %d\n", av_stereo3d_view_from_name("right"));
    لکھو("unspecified: %d\n", av_stereo3d_view_from_name("unspecified"));
    ret = av_stereo3d_view_from_name("nonexistent");
    لکھو("nonexistent: %d\n", ret);

    /* av_stereo3d_primary_eye_name - all valid values */
    لکھو("\nTesting av_stereo3d_primary_eye_name()\n");
    برائے (صحیح i = 0; i <= AV_PRIMARY_EYE_دایاں; i++)
        لکھو("eye %d: %s\n", i, av_stereo3d_primary_eye_name(i));
    لکھو("out of range: %s\n", av_stereo3d_primary_eye_name(100));

    /* av_stereo3d_primary_eye_from_name */
    لکھو("\nTesting av_stereo3d_primary_eye_from_name()\n");
    لکھو("none: %d\n", av_stereo3d_primary_eye_from_name("none"));
    لکھو("left: %d\n", av_stereo3d_primary_eye_from_name("left"));
    لکھو("right: %d\n", av_stereo3d_primary_eye_from_name("right"));
    ret = av_stereo3d_primary_eye_from_name("nonexistent");
    لکھو("nonexistent: %d\n", ret);

    واپس 0;
}
