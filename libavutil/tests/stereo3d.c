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

#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/frame.h"
#अन्तर्भाव "libavutil/macros.h"
#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/stereo3d.h"

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVStereo3D *s3d;
    AVFrame *frame;
    size_t आकार;
    पूर्णाङ्क ret;

    /* av_stereo3d_alloc_size with size output */
    प्रारूप_लिख("Testing av_stereo3d_alloc_size()\n");
    s3d = av_stereo3d_alloc_आकार(&आकार);
    प्रारूप_लिख("alloc_size: %s, size>0: %s\n",
           s3d ? "OK" : "FAIL", आकार > 0 ? "yes" : "no");
    av_free(s3d);

    /* av_stereo3d_alloc (no size) */
    s3d = av_stereo3d_alloc();
    प्रारूप_लिख("alloc: %s\n", s3d ? "OK" : "FAIL");
    av_free(s3d);

    /* av_stereo3d_create_side_data */
    प्रारूप_लिख("\nTesting av_stereo3d_create_side_data()\n");
    frame = av_frame_alloc();
    s3d = av_stereo3d_create_side_दत्त(frame);
    प्रारूप_लिख("create_side_data: %s\n", s3d ? "OK" : "FAIL");
    av_frame_free(&frame);

    /* av_stereo3d_type_name - all valid types */
    प्रारूप_लिख("\nTesting av_stereo3d_type_name()\n");
    प्रति (पूर्णाङ्क i = 0; i <= AV_STEREO3D_UNSPEC; i++)
        प्रारूप_लिख("type %d: %s\n", i, av_stereo3d_type_name(i));
    प्रारूप_लिख("out of range: %s\n", av_stereo3d_type_name(100));

    /* av_stereo3d_from_name - all valid names and unknown */
    प्रारूप_लिख("\nTesting av_stereo3d_from_name()\n");
    {
        स्थिर ध्रुव वर्ण * ध्रुव नामानि[] = {
            "2D", "side by side", "top and bottom", "frame alternate",
            "checkerboard", "side by side (quincunx subsampling)",
            "interleaved lines", "interleaved columns", "unspecified",
        };
        प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(नामानि); i++)
            प्रारूप_लिख("%s: %d\n", नामानि[i], av_stereo3d_from_name(नामानि[i]));
    }
    ret = av_stereo3d_from_name("nonexistent");
    प्रारूप_लिख("nonexistent: %d\n", ret);

    /* av_stereo3d_type_name / av_stereo3d_from_name round-trip */
    प्रारूप_लिख("\nTesting type name round-trip\n");
    प्रति (पूर्णाङ्क i = 0; i <= AV_STEREO3D_UNSPEC; i++) {
        ध्रुव वर्ण *name = av_stereo3d_type_name(i);
        पूर्णाङ्क rt = av_stereo3d_from_name(name);
        प्रारूप_लिख("type roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_name - all valid views */
    प्रारूप_लिख("\nTesting av_stereo3d_view_name()\n");
    प्रति (पूर्णाङ्क i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++)
        प्रारूप_लिख("view %d: %s\n", i, av_stereo3d_view_name(i));
    प्रारूप_लिख("out of range: %s\n", av_stereo3d_view_name(100));

    /* av_stereo3d_view_name / av_stereo3d_view_from_name round-trip */
    प्रारूप_लिख("\nTesting view name round-trip\n");
    प्रति (पूर्णाङ्क i = 0; i <= AV_STEREO3D_VIEW_UNSPEC; i++) {
        ध्रुव वर्ण *name = av_stereo3d_view_name(i);
        पूर्णाङ्क rt = av_stereo3d_view_from_name(name);
        प्रारूप_लिख("view roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_stereo3d_view_from_name */
    प्रारूप_लिख("\nTesting av_stereo3d_view_from_name()\n");
    प्रारूप_लिख("packed: %d\n", av_stereo3d_view_from_name("packed"));
    प्रारूप_लिख("left: %d\n", av_stereo3d_view_from_name("left"));
    प्रारूप_लिख("right: %d\n", av_stereo3d_view_from_name("right"));
    प्रारूप_लिख("unspecified: %d\n", av_stereo3d_view_from_name("unspecified"));
    ret = av_stereo3d_view_from_name("nonexistent");
    प्रारूप_लिख("nonexistent: %d\n", ret);

    /* av_stereo3d_primary_eye_name - all valid values */
    प्रारूप_लिख("\nTesting av_stereo3d_primary_eye_name()\n");
    प्रति (पूर्णाङ्क i = 0; i <= AV_PRIMARY_EYE_दक्षिणः; i++)
        प्रारूप_लिख("eye %d: %s\n", i, av_stereo3d_primary_eye_name(i));
    प्रारूप_लिख("out of range: %s\n", av_stereo3d_primary_eye_name(100));

    /* av_stereo3d_primary_eye_from_name */
    प्रारूप_लिख("\nTesting av_stereo3d_primary_eye_from_name()\n");
    प्रारूप_लिख("none: %d\n", av_stereo3d_primary_eye_from_name("none"));
    प्रारूप_लिख("left: %d\n", av_stereo3d_primary_eye_from_name("left"));
    प्रारूप_लिख("right: %d\n", av_stereo3d_primary_eye_from_name("right"));
    ret = av_stereo3d_primary_eye_from_name("nonexistent");
    प्रारूप_लिख("nonexistent: %d\n", ret);

    प्रत्यागम 0;
}
