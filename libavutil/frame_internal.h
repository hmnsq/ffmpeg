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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ಚೌಕಟ್ಟು_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ಚೌಕಟ್ಟು_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ <stddef.h>

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "frame.h"

/**
 * Allocate the buffer of a video frame like av_frame_get_buffer().
 *
 * @param alloc  allocates the buffer, av_buffer_alloc() is used if NULL
 * @param opaque passed to alloc
 */
ಪೂರ್ಣಾಂಕ ff_ಚೌಕಟ್ಟು_get_video_ಬಫರ್(AVFrame *ಚೌಕಟ್ಟು, ಪೂರ್ಣಾಂಕ align,
                              AVBufferRef *(*alloc)(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2),
                              ಶೂನ್ಯ *opaque);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_FRAME_INTERNAL_H */
