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

#अगर_अघोषित AVUTIL_FILE_OPEN_H
#घोषणा AVUTIL_FILE_OPEN_H

#समावेश <stdio.h>

#समावेश "config.h"
#समावेश "attributes.h"

#अगर HAVE_LIBC_MSVCRT
#घोषणा avpriv_fopen_utf8 ff_fopen_utf8
#घोषणा avpriv_open ff_open
#घोषणा avpriv_tempfile ff_tempfile
#पूर्ण_अगर

 /**
 * A wrapper for open() setting O_CLOEXEC.
 */
av_warn_unused_परिणाम
पूर्णांक avpriv_open(स्थिर अक्षर *filename, पूर्णांक flags, ...);

/**
 * Open a file using a UTF-8 filename.
 */
खाता *avpriv_fopen_utf8(स्थिर अक्षर *path, स्थिर अक्षर *mode);

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
पूर्णांक avpriv_tempfile(स्थिर अक्षर *prefix, अक्षर **filename, पूर्णांक log_offset, व्योम *log_ctx);

#पूर्ण_अगर /* AVUTIL_FILE_OPEN_H */
