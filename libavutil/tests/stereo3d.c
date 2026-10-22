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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/frame.h"
#అన్తర్భావ "libavutil/macros.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/stereo3d.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVStereo3D *s3d;
    AVFrame *చట్రం;
    size_t కొలత;
    పూర్ణాంకం ret;

    /* av_stereo3d_alloc_size with size output */
    రాయి("Testing av_stereo3d_alloc_size()\n");
    s3d = av_stereo3d_alloc_కొలత(&కొలత);
    రాయి("alloc_size: %s, size>0: %s\n",
           s3d ? "OK" : "FAIL", కొలత > 0 ? "yes" : "no");
    av_free(s3d);

    /* av_stereo3d_alloc (no size) */
    s3d = av_stereo3d_alloc();
    రాయి("alloc: %s\n", s3d ? "OK" : "FAIL");
    av_free(s3d);

    /* av_stereo3d_create_side_data */
    రాయి("\nTesting av_stereo3d_create_side_data()\n");
    చట్రం = av_చట్రం_alloc();
    s3d = av_stereo3d_create_side_దత్తాంశం(చట్రం);
    రాయి("create_side_data: %s\n", s3d ? "OK" : "FAIL");
    av_చట్రం_free(&చట్రం);

    /* av_stereo3d_type_name - all valid types */
    రాయి("\nTesting av_stereo3d_type_name()\n");
    కొరకు (పూర్ణాంకం i = 0; i <= AV_STEREO3D_UNSPEC; i++)
        రాయి("type %d: %s\n", i, av_stereo3d_type_name(i));
    రాయి("out of range: %s\n", av_stereo3d_type_name(100));

    /* av_stereo3d_from_name - all valid names and unknown */
    రాయి("\nTesting av_stereo3d_from_name()\n");
    {
        స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి పేర్లు[] = {
            "2D", "side by side", "top and bottom", "frame alternate",
            "checkerboard", "side by side (quincunx subsampling)",
            "interleaved lines", "interleaved columns", "unspecified",
        };
        కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(పేర్లు); i++)
            రాయి("%s: %d\n", పేర్లు[i], av_stereo3d_from_name(పేర్లు[i]));
    }
    ret = av_stereo3d_from_name("nonexistent");
    రాయి("nonexistent: %d\n", ret);

    /* av_stereo3d_type_name / av_stereo3d_from_name round-trip */
    రాయి("\nTesting type name round-trip\n");
    కొరకు (పూర్ణాంకం i = 0; i <= AV_STEREO3D_UNSPEC; i++) {
        స్థిరరాశి అక్షరం *name = av_stereo3d_type_name(i);
        పూర్ణాంకం rt = av_stereo3d_from_name(name);
        రాయి("type roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_name - all valid views */
    రాయి("\nTesting av_stereo3d_view_name()\n");
    కొరకు (పూర్ణాంకం i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++)
        రాయి("view %d: %s\n", i, av_stereo3d_view_name(i));
    రాయి("out of range: %s\n", av_stereo3d_view_name(100));

    /* av_stereo3d_view_name / av_stereo3d_view_from_name round-trip */
    రాయి("\nTesting view name round-trip\n");
    కొరకు (పూర్ణాంకం i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++) {
        స్థిరరాశి అక్షరం *name = av_stereo3d_view_name(i);
        పూర్ణాంకం rt = av_stereo3d_view_from_name(name);
        రాయి("view roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_from_name */
    రాయి("\nTesting av_stereo3d_view_from_name()\n");
    రాయి("packed: %d\n", av_stereo3d_view_from_name("packed"));
    రాయి("left: %d\n", av_stereo3d_view_from_name("left"));
    రాయి("right: %d\n", av_stereo3d_view_from_name("right"));
    రాయి("unspecified: %d\n", av_stereo3d_view_from_name("unspecified"));
    ret = av_stereo3d_view_from_name("nonexistent");
    రాయి("nonexistent: %d\n", ret);

    /* av_stereo3d_primary_eye_name - all valid values */
    రాయి("\nTesting av_stereo3d_primary_eye_name()\n");
    కొరకు (పూర్ణాంకం i = 0; i <= AV_PRIMARY_EYE_కుడి; i++)
        రాయి("eye %d: %s\n", i, av_stereo3d_primary_eye_name(i));
    రాయి("out of range: %s\n", av_stereo3d_primary_eye_name(100));

    /* av_stereo3d_primary_eye_from_name */
    రాయి("\nTesting av_stereo3d_primary_eye_from_name()\n");
    రాయి("none: %d\n", av_stereo3d_primary_eye_from_name("none"));
    రాయి("left: %d\n", av_stereo3d_primary_eye_from_name("left"));
    రాయి("right: %d\n", av_stereo3d_primary_eye_from_name("right"));
    ret = av_stereo3d_primary_eye_from_name("nonexistent");
    రాయి("nonexistent: %d\n", ret);

    తిరిగి 0;
}
