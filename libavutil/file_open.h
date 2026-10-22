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

#اگر_غیر_تعریف_شدہ AVUTIL_FILE_OPEN_H
#تعریف_کرو AVUTIL_FILE_OPEN_H

#شامل <stdio.h>

#شامل "config.h"
#شامل "attributes.h"

#اگر HAVE_LIBC_MSVCRT
#تعریف_کرو avpriv_fopen_utf8 ff_fopen_utf8
#تعریف_کرو avpriv_open ff_open
#تعریف_کرو avpriv_tempfile ff_tempfile
#اگر_ختم

 /**
 * A wrapper for open() setting O_CLOEXEC.
 */
av_warn_غیر_مستعمل_نتیجہ
صحیح avpriv_open(ثابت حرف *filename, صحیح flags, ...);

/**
 * Open a file using a UTF-8 filename.
 */
FILE *avpriv_fopen_utf8(ثابت حرف *راستہ, ثابت حرف *منوال);

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
صحیح avpriv_tempfile(ثابت حرف *سابقہ, حرف **filename, صحیح log_انحراف, خالی *log_ctx);

#اگر_ختم /* AVUTIL_FILE_OPEN_H */
