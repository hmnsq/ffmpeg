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

#اگر_تعریف_نشده AVUTIL_قاب_داخلی_H
#تعریف_کن AVUTIL_قاب_داخلی_H

#ضمن <stddef.h>

#ضمن "buffer.h"
#ضمن "frame.h"

/**
 * Allocate the buffer of a video frame like av_frame_get_buffer().
 *
 * @param alloc  allocates the buffer, av_buffer_alloc() is used if NULL
 * @param opaque passed to alloc
 */
صحيح ff_قاب_get_video_میانگیر(AVFrame *قاب, صحيح align,
                              AVBufferRef *(*alloc)(فراغ *opaque, size_t اندازه),
                              فراغ *opaque);

#پایان_اگر /* AVUTIL_FRAME_INTERNAL_H */
