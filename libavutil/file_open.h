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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_FILE_OPEN_H
#وصف_ڪريو AVUTIL_FILE_OPEN_H

#ضمن <stdio.h>

#ضمن "config.h"
#ضمن "attributes.h"

#إذا HAVE_LIBC_MSVCRT
#وصف_ڪريو avpriv_fopen_utf8 ff_fopen_utf8
#وصف_ڪريو avpriv_open ff_open
#وصف_ڪريو avpriv_tempfile ff_tempfile
#جيڪڏهن_پورو

 /**
 * A wrapper for open() setting O_CLOEXEC.
 */
av_warn_اڻ_استعمال_ٿيل_نتيجو
صحيح avpriv_open(ثابت حرف *filename, صحيح flags, ...);

/**
 * Open a file using a UTF-8 filename.
 */
FILE *avpriv_fopen_utf8(ثابت حرف *رستو, ثابت حرف *گهڻائي);

/**
 * Wrapper to work around the lack of mkstemp() on mingw.
 * Also, tries to create file in /tmp first, if possible.
 * *prefix can be a character constant; *filename will be allocated internally.
 * @return file descriptor of opened file (or negative value corresponding to an
 * AVERROR code on error)
 * and opened file name in **filename.
 * @note On very old libcs it is necessary to set a secure umask before
 *       calling this, av_tempfile() can't call umask itself as it is used in
 *       libraries and could interfere with the calling application.
 */
صحيح avpriv_tempfile(ثابت حرف *اڳياڙي, حرف **filename, صحيح log_وٿي, فراغ *log_ctx);

#جيڪڏهن_پورو /* AVUTIL_FILE_OPEN_H */
