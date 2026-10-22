/*
 * Copyright (c) 2013 Vittorio Giovara <vittorio.giovara@gmail.com>
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

/**
 * @file
 * @ingroup lavu_video_stereo3d
 * Stereoscopic video
 */

#ifndef AVUTIL_STEREO3D_H
#define AVUTIL_STEREO3D_H

#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "frame.h"

/**
 * @defgroup lavu_video_stereo3d Stereo3D types and functions
 * @ingroup lavu_video
 *
 * A stereoscopic video file consists in multiple views embedded in a single
 * frame, usually describing two views of a scene. This file describes all
 * possible codec-independent view arrangements.
 *
 * @{
 */

/**
 * List of possible 3D Types
 */
গণনা AVStereo3DType {
    /**
     * Video is not stereoscopic (and metadata has to be there).
     */
    AV_STEREO3D_2D,

    /**
     * Views are next to each other.
     *
     * @code{.unparsed}
     *    LLLLRRRR
     *    LLLLRRRR
     *    LLLLRRRR
     *    ...
     * @endcode
     */
    AV_STEREO3D_SIDEBYSIDE,

    /**
     * Views are on top of each other.
     *
     * @code{.unparsed}
     *    LLLLLLLL
     *    LLLLLLLL
     *    RRRRRRRR
     *    RRRRRRRR
     * @endcode
     */
    AV_STEREO3D_TOPBOTTOM,

    /**
     * Views are alternated temporally.
     *
     * @code{.unparsed}
     *     frame0   frame1   frame2   ...
     *    LLLLLLLL RRRRRRRR LLLLLLLL
     *    LLLLLLLL RRRRRRRR LLLLLLLL
     *    LLLLLLLL RRRRRRRR LLLLLLLL
     *    ...      ...      ...
     * @endcode
     */
    AV_STEREO3D_FRAMESEQUENCE,

    /**
     * Views are packed in a checkerboard-like structure per pixel.
     *
     * @code{.unparsed}
     *    LRLRLRLR
     *    RLRLRLRL
     *    LRLRLRLR
     *    ...
     * @endcode
     */
    AV_STEREO3D_CHECKERBOARD,

    /**
     * Views are next to each other, but when upscaling
     * apply a checkerboard pattern.
     *
     * @code{.unparsed}
     *     LLLLRRRR          L L L L    R R R R
     *     LLLLRRRR    =>     L L L L  R R R R
     *     LLLLRRRR          L L L L    R R R R
     *     LLLLRRRR           L L L L  R R R R
     * @endcode
     */
    AV_STEREO3D_SIDEBYSIDE_QUINCUNX,

    /**
     * Views are packed per line, as if interlaced.
     *
     * @code{.unparsed}
     *    LLLLLLLL
     *    RRRRRRRR
     *    LLLLLLLL
     *    ...
     * @endcode
     */
    AV_STEREO3_D_সারিগুলি,

    /**
     * Views are packed per column.
     *
     * @code{.unparsed}
     *    LRLRLRLR
     *    LRLRLRLR
     *    LRLRLRLR
     *    ...
     * @endcode
     */
    AV_STEREO3D_COLUMNS,

    /**
     * Video is stereoscopic but the packing is unspecified.
     */
    AV_STEREO3D_UNSPEC,
};

/**
 * List of possible view types.
 */
গণনা AVStereo3DView {
    /**
     * Frame contains two packed views.
     */
    AV_STEREO3D_VIEW_PACKED,

    /**
     * Frame contains only the left view.
     */
    AV_STEREO3_D_VIEW_বাম,

    /**
     * Frame contains only the right view.
     */
    AV_STEREO3_D_VIEW_ডান,

    /**
     * Content is unspecified.
     */
    AV_STEREO3D_VIEW_UNSPEC,
};

/**
 * List of possible primary eyes.
 */
গণনা AVStereo3DPrimaryEye {
    /**
     * Neither eye.
     */
    AV_PRIMARY_EYE_NONE,

    /**
     * Left eye.
     */
    AV_PRIMARY_EYE_বাম,

    /**
     * Right eye
     */
    AV_PRIMARY_EYE_ডান,
};

/**
 * Inverted views, Right/Bottom represents the left view.
 */
#define AV_STEREO3D_FLAG_INVERT     (1 << 0)

/**
 * Stereo 3D type: this structure describes how two videos are packed
 * within a single video surface, with additional information as needed.
 *
 * @note The struct must be allocated with av_stereo3d_alloc() and
 *       its size is not a part of the public ABI.
 */
প্রকারলেখ কাঠামো AVStereo3D {
    /**
     * How views are packed within the video.
     */
    গণনা AVStereo3DType type;

    /**
     * Additional information about the frame packing.
     */
    পূর্ণসংখ্যা flags;

    /**
     * Determines which views are packed.
     */
    গণনা AVStereo3DView view;

    /**
     * Which eye is the primary eye when rendering in 2D.
     */
    গণনা AVStereo3DPrimaryEye primary_eye;

    /**
     * The distance between the centres of the lenses of the camera system,
     * in micrometers. Zero if unset.
     */
    uint32_t baseline;

    /**
     * Relative shift of the left and right images, which changes the zero parallax plane.
     * Range is -1.0 to 1.0. Zero if unset.
     */
    AVRational horizontal_disparity_adjustment;

    /**
     * Horizontal field of view, in degrees. Zero if unset.
     */
    AVRational horizontal_field_of_view;
} AVStereo3D;

/**
 * Allocate an AVStereo3D structure and set its fields to default values.
 * The resulting struct can be freed using av_freep().
 *
 * @return An AVStereo3D filled with default values or NULL on failure.
 */
AVStereo3D *av_stereo3d_alloc(শূন্য);

/**
 * Allocate an AVStereo3D structure and set its fields to default values.
 * The resulting struct can be freed using av_freep().
 *
 * @return An AVStereo3D filled with default values or NULL on failure.
 */
AVStereo3D *av_stereo3d_alloc_আকার(size_t *আকার_2);

/**
 * Allocate a complete AVFrameSideData and add it to the frame.
 *
 * @param frame The frame which side data is added to.
 *
 * @return The AVStereo3D structure to be filled by caller.
 */
AVStereo3D *av_stereo3d_create_side_তথ্য(AVFrame *frame);

/**
 * Provide a human-readable name of a given stereo3d type.
 *
 * @param type The input stereo3d type value.
 *
 * @return The name of the stereo3d value, or "unknown".
 */
ধ্রুবক অক্ষর *av_stereo3d_type_name(unsigned পূর্ণসংখ্যা type);

/**
 * Get the AVStereo3DType form a human-readable name.
 *
 * @param name The input string.
 *
 * @return The AVStereo3DType value, or -1 if not found.
 */
পূর্ণসংখ্যা av_stereo3d_from_name(ধ্রুবক অক্ষর *name);

/**
 * Provide a human-readable name of a given stereo3d view.
 *
 * @param type The input stereo3d view value.
 *
 * @return The name of the stereo3d view value, or "unknown".
 */
ধ্রুবক অক্ষর *av_stereo3d_view_name(unsigned পূর্ণসংখ্যা view);

/**
 * Get the AVStereo3DView form a human-readable name.
 *
 * @param name The input string.
 *
 * @return The AVStereo3DView value, or -1 if not found.
 */
পূর্ণসংখ্যা av_stereo3d_view_from_name(ধ্রুবক অক্ষর *name);

/**
 * Provide a human-readable name of a given stereo3d primary eye.
 *
 * @param type The input stereo3d primary eye value.
 *
 * @return The name of the stereo3d primary eye value, or "unknown".
 */
ধ্রুবক অক্ষর *av_stereo3d_primary_eye_name(unsigned পূর্ণসংখ্যা eye);

/**
 * Get the AVStereo3DPrimaryEye form a human-readable name.
 *
 * @param name The input string.
 *
 * @return The AVStereo3DPrimaryEye value, or -1 if not found.
 */
পূর্ণসংখ্যা av_stereo3d_primary_eye_from_name(ধ্রুবক অক্ষর *name);

/**
 * @}
 */

#endif /* AVUTIL_STEREO3D_H */
