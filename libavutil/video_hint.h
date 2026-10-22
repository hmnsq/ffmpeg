/**
 * Copyright 2023 Elias Carotti <eliascrt at amazon dot it>
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

#अगर_अघोषित AVUTIL_VIDEO_HINT_H
#घोषणा AVUTIL_VIDEO_HINT_H

#समावेश <stddef.h>
#समावेश <stdint.h>
#समावेश "libavutil/avassert.h"
#समावेश "libavutil/frame.h"

प्रकार काष्ठा AVVideoRect {
    uint32_t x, y;
    uint32_t width, height;
} AVVideoRect;

प्रकार क्रमागत AVVideoHintType {
    /* rectangled delimit the constant areas (unchanged), default is changed */
    AV_VIDEO_HINT_TYPE_CONSTANT,

    /* rectangled delimit the constant areas (changed), default is not changed */
    AV_VIDEO_HINT_TYPE_CHANGED,
} AVVideoHintType;

प्रकार काष्ठा AVVideoHint {
    /**
     * Number of AVVideoRect present.
     *
     * May be 0, in which case no per-rectangle information is present. In this
     * case the values of rect_offset / rect_size are unspecified and should
     * not be accessed.
     */
    माप_प्रकार nb_rects;

    /**
     * Offset in bytes from the beginning of this structure at which the array
     * of AVVideoRect starts.
     */
    माप_प्रकार rect_offset;

    /**
     * Size in bytes of AVVideoRect.
     */
    माप_प्रकार rect_आकार;

    AVVideoHintType type;
} AVVideoHint;

अटल av_always_inline AVVideoRect *
av_video_hint_rects(स्थिर AVVideoHint *hints) {
    वापस (AVVideoRect *)((uint8_t *)hints + hints->rect_offset);
}

अटल av_always_inline AVVideoRect *
av_video_hint_get_rect(स्थिर AVVideoHint *hints, माप_प्रकार idx) {
    वापस (AVVideoRect *)((uint8_t *)hints + hints->rect_offset + idx * hints->rect_आकार);
}

/**
 * Allocate memory for the AVVideoHint struct along with an nb_rects-sized
 * arrays of AVVideoRect.
 *
 * The side data contains a list of rectangles for the portions of the frame
 * which changed from the last encoded one (and the remainder are assumed to be
 * changed), or, alternately (depending on the type parameter) the unchanged
 * ones (and the remaining ones are those which changed).
 * Macroblocks will thus be hinted either to be P_SKIP-ped or go through the
 * regular encoding procedure.
 *
 * It's responsibility of the caller to fill the AVRects accordingly, and to set
 * the proper AVVideoHintType field.
 *
 * @param out_size if non-NULL, the size in bytes of the resulting data array is
 *                 written here
 *
 * @return newly allocated AVVideoHint struct (must be freed by the caller using
 *         av_free()) on success, NULL on memory allocation failure
 */
AVVideoHint *av_video_hint_alloc(माप_प्रकार nb_rects,
                                 माप_प्रकार *out_आकार);

/**
 * Same as av_video_hint_alloc(), except newly-allocated AVVideoHint is attached
 * as side data of type AV_FRAME_DATA_VIDEO_HINT_INFO to frame.
 */
AVVideoHint *av_video_hint_create_side_तथ्य(AVFrame *frame,
                                            माप_प्रकार nb_rects);


#पूर्ण_अगर /* AVUTIL_VIDEO_HINT_H */
